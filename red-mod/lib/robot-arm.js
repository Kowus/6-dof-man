'use strict';
class RobotArm {
  constructor({ name, address, max_angle, keep_enabled }) {
    this.name = name;
    this.address = address;
    this.max_angle = max_angle || 270;
    this.keep_enabled = keep_enabled;
  }
}
module.exports = RobotArm;
