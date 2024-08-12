// models/queryModel.js
const mongoose = require('mongoose');

const adminDataSchema = new mongoose.Schema({
    adminid: {
        type: String,
        unique: true,
        required: true
      },
      password: {
        type: String,
        required: true
      }
});

const adminData = mongoose.model('adminData', adminDataSchema);

module.exports = adminData;
