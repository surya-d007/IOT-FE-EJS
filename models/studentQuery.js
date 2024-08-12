  // models/queryModel.js
  const mongoose = require('mongoose');

  const studentQuerySchema = new mongoose.Schema({
    name: String,
    registerNo: String,
    phoneNo: String,
    queries: [
      {
        querytitle: {
          type: String,
        },
        query: {
          type: String
        }
      }
    ],
    stundentid : String , 
    studentQueryid : String,  

  });

  const studentQuery = mongoose.model('studentQuery', studentQuerySchema);

  module.exports = studentQuery;
