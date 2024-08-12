// app.js
const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const session = require('express-session');
const studentDataModel = require('./models/studentData');
const studentQueryModel = require('./models/studentQuery');
const AdminData = require('./models/adminData');

const app = express();
const port = 3000;

// Connect to MongoDB
mongoose.connect('mongodb+srv://surya-007:abcd1234@cluster0.e95bgae.mongodb.net/SmartFacilityManagementSystem', { useNewUrlParser: true, useUnifiedTopology: true });
const db = mongoose.connection;

// Check MongoDB connection
db.on('error', console.error.bind(console, 'MongoDB connection error:'));
db.once('open', () => {
  console.log('Connected to MongoDB');
});

// Middleware to parse incoming requests
app.use(bodyParser.urlencoded({ extended: true }));

// Use session middleware
app.use(session({ secret: 'your-secret-key', resave: true, saveUninitialized: true }));

// Set EJS as the view engine
app.set('view engine', 'ejs');
app.use(express.static('public'));
// Routes
app.get('/', (req, res) => {
  res.redirect('/login');
});

app.get('/login', (req, res) => {
  res.render('login');
});

app.post('/student/login', async (req, res) => {
  const { registerNo, password } = req.body;

  try {
    const student = await studentDataModel.findOne({ registerNo, password });

    if (student) {
      req.session.student = {
        registerNo: student.registerNo,
        name: student.name,
        phoneNo: student.phoneNo,
        studentid: student._id
      };

      res.render('studentHome', { student });
    } else {
      res.send("Invalid credentials");
    }
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/student/register', (req, res) => {
  res.render('student-register');
});

app.get('/admin/register', (req, res) => {
  // Render the admin registration form using EJS
  res.render('adminRegistration');
});




app.post('/student/register', async (req, res) => {
  const { registerNo, password, phoneNo, name } = req.body;
  const student = new studentDataModel({
    registerNo,
    password,
    name,
    phoneNo
  });

  try {
    const savedUserData = await student.save();

    req.session.student = {
      registerNo: student.registerNo,
      name: student.name,
      phoneNo: student.phoneNo,
      studentid: student._id
    };

    res.redirect('/student/home');
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});

app.get('/student/home', (req, res) => {

  const data = req.session.student;
  const student =  studentDataModel.findOne(data.registerNo);
  res.render('studentHome', { student });
});


app.post('/admin/register', (req, res) => {
  // Extract admin registration details from request body
  const { registerNo, password } = req.body;

  // Create a new admin data document
  const newAdmin = new AdminData({
      adminid: registerNo,
      password: password
  });

  // Save the admin data to the database
  newAdmin.save()
      .then(() => {
          console.log('Admin registered successfully');
           res.redirect('/admin/home');
      })
      .catch(err => {
          console.error('Error registering admin:', err);
          res.status(500).send('Error registering admin');
      });
});





app.post('/student/raisequery', async (req, res) => {
  const { querytitle, query } = req.body;
  const student = req.session.student;

  try {
    if (!student) {
      return res.status(401).send('Unauthorized');
    }

    // Retrieve the student's ID from the session
    const studentId = student.studentid;

    // Find the student in the database by ID
    const foundStudent = await studentDataModel.findById(studentId);

    if (foundStudent) {
      // Add the new query to the student's queries array
      foundStudent.queries.push({
        querytitle: querytitle,
        query: query
      });
      await foundStudent.save();




      const newStudentQuery = new studentQueryModel({
        name: foundStudent.name,
        registerNo: foundStudent.registerNo,
        phoneNo: foundStudent.phoneNo,
        queries: [{ querytitle, query }],
        studentid: foundStudent._id,
      });
      // Save the new studentQuery document to the database
       newStudentQuery.save();
       res.render('studentHome',{student : foundStudent});
    } else {
      res.status(404).send('Student not found');
    }
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});




app.get('/admin/home', async (req, res) => {
  try {
    // Retrieve all data from studentQueryModel
    const allQueries = await studentQueryModel.find();

    // Render the admin home view and pass the retrieved data
    res.render('adminHome', { queries: allQueries });
  } catch (error) {
    console.error(error);
    res.status(500).send('Internal Server Error');
  }
});



// Start the server
app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}`);
});
