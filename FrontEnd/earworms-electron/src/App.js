import React from 'react';
import { Switch, Route } from 'react-router'
import logo from './logo.svg';
import './App.css';
import Settings from './pages/settings';
import Main from './pages/Main';

class App extends Component{
  state = {}
  render(){
    return(
      <Switch>
        <Route path='settings' Component={Settings} />
        <Route path='/' Component={Main}/>
      </Switch>
    )
  }
}

export default App;
