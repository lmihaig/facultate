const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  devServer: {
    proxy: 'http://' + process.env.PROXY_API + ':5000'
  }
})


