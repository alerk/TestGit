//expressex.js
var app = angular.module('ExpressEx', ['ngResource', 'ngRoute']);

app.config(['$routeProvider', function($routeProvider){
    $routeProvider
        .when('/', {
            templateUrl: 'partials/home.html',
            controller: 'HomeCtrl'
        })
        .when('/add-video', {
            templateUrl: 'partials/video-form.html',
            controller: 'AddVideoCtrl'
        })
        .when('/video/:id', {
            templateUrl: 'partials/video-form.html',
            controller: 'EditVideoCtrl'
        })
        .when('/del-video/:id', {
            templateUrl: 'partials/confirm-form.html',
            controller: 'DelVideoCtrl'
        })
        .otherwise({
            redirectTo: '/'
        });
}]);

app.controller('HomeCtrl', ['$scope', '$resource', 
    function($scope, $resource) {
        var Videos = $resource('/videos');
        Videos.query(function(videos){
            $scope.videos = videos;
        });
    }]);

app.controller('AddVideoCtrl', ['$scope', '$resource', '$location', 
    function($scope, $resource, $location){
        $scope._save = function() {
            var Videos = $resource('/videos');
            Videos.save($scope.video, function(){
                $location.path('/');
            });//Videos.save function
        };//scope.save function
    }]);//app.controller function

app.controller('EditVideoCtrl', ['$scope', '$resource', '$location', '$routeParams',
    function($scope, $resource, $location, $routeParams){
        var Videos = $resource('/videos/:id', {id: '@_id'}, {
            update: { method: 'PUT' }
        }); //Extend the $resource, map Videos.update function to method PUT in video.js

        //get the current video object inside the db with id = $routeParams.id 
        //and apply to the $scope.video
        Videos.get({ id: $routeParams.id }, function(video){
            $scope.video = video;
        }); 

        $scope._save = function() {
            Videos.update($scope.video, function() {
                $location.path('/');
            }); // This function will be called when user pressed the "Save" button
        };
    }]);

app.controller('DelVideoCtrl', ['$scope', '$resource', '$location', '$routeParams', 
    function($scope, $resource, $location, $routeParams){
        var Videos = $resource('/videos/:id');
        Videos.get({ id: $routeParams.id }, function(video) {
            $scope.video = video;
        });

        $scope._del = function() {
            Videos.delete({ id: $routeParams.id }, function(video) {
                $location.path('/');
            });//Videos.save function
        };//scope._del function
    }]);//app.controller function