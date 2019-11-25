import React,{ Component} from 'react';
import logo from './logo.svg';
import './App.css';

class App extends Component{
  state = {}
  render(){
    return(
      <div>
        <div className = "IP address"> IP Address </div>
        <input type = "text"/>

        <div className = "IP address"> Name </div>
        <input type = "text"/>
      </div>
    )
  }
}

export default App;
