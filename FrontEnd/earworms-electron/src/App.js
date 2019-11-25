import React,{ Component} from 'react';
// import logo from './logo.svg';
import './App.css';

const electron = window.require('electron');
const fs = electron.remote.require('fs');
const ipcRenderer  = electron.ipcRenderer;

class App extends Component{
  state = {}
  render(){
    return(
      <div className = "loginMain">
        <script>
          window.require = require
        </script>
        <div className = "IP"> IP Address </div>
        <input type = "text"/>

        <div className = "name"> Name </div>
        <input type = "text"/>
      </div>
    )
  }
}

export default App;
