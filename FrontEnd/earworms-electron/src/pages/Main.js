import React from 'react';


const electron = window.require('electron');
const fs = electron.remote.require('fs');
const ipcRenderer  = electron.ipcRenderer;

class Main extends Component{
  constructor(props){
    super(props);
    this.state = {}
    ipcRenderer.on('hello', (event, arg) =>{
      console.log(arg);
    })
  }

  buttonPressed = () => {
    ipcRenderer.send('hello', 'hiii')
  }

	render(){
      <div className = "loginMain">
        <script>
          window.require = require
        </script>
        <div className = "IP"> IP Address </div>
        <input type = "text"/>

        <div className = "name"> Name </div>
        <input type = "text"/>
      
        <button onClick={this.buttonPressed}> Hello! </button>
      </div>
    }
}

export default Main;