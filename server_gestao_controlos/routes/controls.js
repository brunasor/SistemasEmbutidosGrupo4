var express = require('express');
var router = express.Router();


router.get('/forward', function (req, res, next) {
    res.send("forward");
});
router.get('/backward', function (req, res, next) {
    res.send("backward");
});
router.get('/left', function (req, res, next) {
    res.send("left");
});
router.get('/right', function (req, res, next) {
    res.send("right");
});

router.get('/stop', function (req, res, next) {
    res.send("stop");
});


module.exports = router;
