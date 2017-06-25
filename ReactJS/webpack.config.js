const path = require("path");
const config = {
entry: [
    'webpack-dev-server/client?http://0.0.0.0:8080',
    'webpack/hot/only-dev-server',
     config.paths.demo
],
plugins:[
  new webpack.HotModuleReplacementPlugin()
],
output: {
  path: path.resolve(__dirname, "dist"),
  filename: "Main.js"
},
module: {
  loaders: [
  {
      test:/\.(js|jsx)$/,
      loader: "babel-loader",
      query: {
          presets: ["react", "es2016"]
      }
  }
]
}
};
 
module.exports = config;