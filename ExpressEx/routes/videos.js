var express = require('express');
var router = express.Router();

var monk = require('monk');
//DB name is ExpressEx
var db = monk('localhost:27017/ExpressEx'); 

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
    collection.update({_id: req.params.id}, 
        {
            title: req.body.title,
            description: req.body.description
        }, //Params of the put
        function (err, video) {
            if (err) {
                throw err;
            }
            res.json(video);
    });
});

//Delete a video
router.delete('/:id', function(res, req) {
    var collection = db.get('videos');
    collection.remove({ _id: req.params.id }, 
        function (err, video) {
            if (err) {
                throw err;
            }
            res.json(video);
    });
});

module.exports = router;