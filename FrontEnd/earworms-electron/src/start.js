const electron = require('electron')
const app = electron.app
const BrowserWindow = electron.BrowserWindow

const path = require('path')

let mainWindow;

let connectionInfo = {
  host: '',
  port: 24825,
  pollFrequency: 1000
}

function createWindow() {
  // mainWindow = new BrowserWindow({ width: 350, height: 200, frame  : false })

  console.log("creating Window")
  const {net, ipcMain} = require('electron')
  const request = require('request');  

  mainWindow = new BrowserWindow({ 
    width: 411, 
    // width: 800, 
    height: 731, 
    frame: false,
    // frame: true,
    webPreferences: {
      nodeIntegration: true,
    }
  })

  mainWindow.loadURL('http://localhost:3000');
  mainWindow.setAlwaysOnTop(true)
  // mainWindow.setResizable(false)
  mainWindow.on('closed', () => {
    mainWindow = null
  })

  ipcMain.on('set-connection-info', (event, args) => {
    console.log('Set Connection Info', args)
    connectionInfo = {
      ...connectionInfo,
      ...args
    };
    event.reply('get-connection-info', connectionInfo);
  })

  ipcMain.on('sending_vote', (event, args) => {
    var vote = JSON.stringify({'vote': args, 'cid': 'shawarma'});
    sendVote("POST", 'songs/votes', vote)

  })

  function sendVote(type, url, value = ""){
    request({ 
      body: value, 
      followAllRedirects: true,
      headers: {
        'Content-Type': 'application/json',
      },
      method: type,
      url: 'http://smaug:24824/' + url}, callback);

    function callback(error, response, body) {
      if (!error && response.statusCode == 200) {
          jsonBody = JSON.parse(body)
          console.log("sendVote: received");
          console.log(jsonBody);
      } else {
          console.log("Error: \n"+body);
      }
    };
  }


  /// TODO: need to handle callback seperately
  function sendRequest(type, url, value = ""){
    console.log("SENDING REQUEST:", type, url);
    request({ 
      body: value, 
      followAllRedirects: true,
      headers: {
        'Content-Type': 'application/json',
      },
      method: type,
      url: 'http://smaug:24824/' + url}, callback);

    function callback(error, response, body) {
      if (!error && response.statusCode == 200) {
          jsonBody = JSON.parse(body)
          console.log("received");
          console.log(jsonBody);
          mainWindow.webContents.send('currentSong', jsonBody);
      } else {
          console.log("Error: \n"+error);
      }
    };
  }

  function updateCurrentSong(){
    console.log("updting current song");
    var randomCid = JSON.stringify({'cid': 'shawarma'});
    sendRequest('GET',  "songs/current", randomCid);
  }

  const updater = setInterval(updateCurrentSong, 1000);

}

app.on('ready', createWindow)

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

app.on('activate', () => {
  if (mainWindow === null) {
    createWindow()
  }
})