const i2c = require('i2c-bus');
const RobotArm = require('../lib/robot-arm');

const Shoulder = new RobotArm({
  name: 'Shoulder',
  address: '1',
  keep_enabled = false
});
