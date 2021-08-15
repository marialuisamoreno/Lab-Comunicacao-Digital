const express = require('express');
const router = express.Router();

const { Controller } = require('./controller');

router.get('/', (req, res, next) => {
    res.sendFile(__dirname + '/index.html');
});

router.get('/joystick', (req, res, next) => {
    Controller.joystick(req.query)
    res.sendFile(__dirname + '/index.html');
});

module.exports = router;