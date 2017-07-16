var webpack = require('webpack');
var WebpackDevServer = require('webpack-dev-server');
var config = require('./webpack.config.js');

var port = 8081;
new WebpackDevServer(webpack(config),{
    publicPath:'/',
    hot: true,
    historyApiFallback: true,
    stats: { colors: true }
}).listen(port, '0.0.0.0', function(err) {
    if (err) {
        console.log(err);
    }
    console.log('::: Server is running ::: ==> 0.0.0.0:' + port);
});