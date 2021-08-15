const express = require('express');
const app = express();
const server = require('http').createServer(app);

const router = require('./router');

app.use('/', router);

const port = 1234;
server.listen(port, () => {
    console.log(`Server listening on port ${port}`);
});