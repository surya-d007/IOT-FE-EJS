const mongoose = require('mongoose');

const studentDataSchema = new mongoose.Schema({
  registerNo: {
    type: String,
    unique: true,
    required: true
  },
  password: {
    type: String,
    required: true
  },
  name: {
    type: String,
    required: true
  },
  phoneNo: {
    type: String,
    required: true
  },
  queries: [
    {
      querytitle: {
        type: String
      },
      query: {
        type: mongoose.Schema.Types.Mixed
      }
    }
  ]
});

const StudentData = mongoose.model('StudentData', studentDataSchema);

module.exports = StudentData;
