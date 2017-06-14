// #Node
var express = require('express');
var router = express.Router();

var monk = require('monk');
//DB name is ExpressEx
var db = monk('192.168.128.5:27017/ExpressEx'); 

router.get('/', function(req,res) {
    var collection = db.get('videos');
    collection.find({}, function(err, videos){
        if (err) {
            throw err;
        }
        res.json(videos);
    });
});

//Add new video
router.post('/', function(req, res){
    var collection = db.get('videos');
    collection.insert({
        title: req.body.title,
        description: req.body.description
    }, function(err, video) {
        if (err) {
            throw err;
        }
        res.json(video);
    });
});

//Get video info - To display 1 for editing
router.get('/:id', function(req, res){
    var collection = db.get('videos');
    collection.findOne({ _id: req.params.id}, function(err, video){
        if (err) {
            throw err;
        }
        res.json(video);
    });
});

//Put video info - To update info of 1 video
router.put('/:id', function(res, req) {
    var collection = db.get('videos');
    console.log("router.put is called");
    collection.findById(req.params.id, function(error, video) {
        console.log("findById");
        if(error) {
            return res.send(500, error);
        }
        if (!video) {
            return res.send(404);
        }
        var updateValue = {title: req.body.title, description: req.body.description};
        collection.updateById(req.params.id, /*Params of the put*/ updateValue,  function (err, video) {
            console.log("updateById");
            if (err) {
                return res.send(500, err);
            }
            res.json(video);
        });
    });
});

// Delete a video
router.delete('/:id', function(res, req) {
    var collection = db.get('videos');

    collection.remove({ _id: req.params.id }, 
        function (err, video) {
            console.log("router.delete is called");
            if (err) {
                throw err;
            }
            res.json(video);
    });
});

module.exports = router;