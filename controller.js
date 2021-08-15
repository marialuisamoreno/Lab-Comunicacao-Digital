const SerialPort = require('serialport');
const port = new SerialPort('COM6', { baudRate: 57600 });

port.on('data', data => {
    console.log('got word from arduino:', data.toString());
});

class Controller {
    static joystick({ dir }) {
        port.write(dir, (err) => {
            if (err) {
              return console.log('Error on write: ', err.message);
            }
            console.log('message written');
        });
    }
}

module.exports = { Controller, controller: new Controller() };


