import React, {Component} from 'react';
import {Redirect} from 'react-router-dom';
import './Settings.css';
import Logo from '../assets/logo.svg';
const {ipcRenderer} = window.require('electron');

class Settings extends Component {
    constructor() {
        super();
        this.state = {
            shouldRedirect: false,
            ipOne: '',
            ipTwo: '',
            ipThree: '',
            ipFour: ''
        };
        ipcRenderer.on('get-connection-info', (event, args) => {
            const {host} = args;
            console.log('Get Connection Info', host);
            const [one, two, three, four] = host.split('.')
            this.setState({
                ipOne: one,
                ipTwo: two,
                ipThree: three,
                ipFour: four
            });
        });
        ipcRenderer.send('set-connection-info', {})
        this.handleSubmit = this.handleSubmit.bind(this);
        this.handleInput = this.handleInput.bind(this);
    }

    handleInput(event) {
        const {name, value} = event.target;
        const numValue = parseInt(value);
        console.log(numValue);
        if (value === '' || (Number.isInteger(numValue) && numValue < 1000 && numValue >= 0))
        {
            this.setState({
                [name]: numValue || value.slice(0,3)
            });
        }
    }

    handleSubmit() {
        const { ipOne, ipTwo, ipThree, ipFour } = this.state;
        if (ipOne !== '' && ipTwo !== '' && ipThree !== '' && ipFour !== '') {
            ipcRenderer.send('set-connection-info', {
                host: `${ipOne}.${ipTwo}.${ipThree}.${ipFour}`
            });
        } else {
            console.error('Cannot send message');
        }
        this.setState({shouldRedirect: true});
    }

    render() {
        const {
            shouldRedirect,
            ipOne,
            ipTwo,
            ipThree,
            ipFour
        } = this.state;
        if (shouldRedirect) {
            return (<Redirect to='/main'/>);
        } else {
            return (
                <div className="loginMain"> 
                    <img className="logo" src={Logo} alt='Earworms'></img>
                    <div className="ip-label">Host IP</div>
                    <input type="text" name="ipOne" value={ipOne} onChange={this.handleInput} className="ip-address-control"/>
                    <input type="text" name="ipTwo" value={ipTwo} onChange={this.handleInput} className="ip-address-control"/>
                    <input type="text" name="ipThree" value={ipThree} onChange={this.handleInput} className="ip-address-control"/>
                    <input type="text" name="ipFour" value={ipFour} onChange={this.handleInput} className="ip-address-control"/>
                    <button type='button' className="join-btn" onClick={this.handleSubmit}>Join the Party!</button>
                </div>
            );
        }
    }
}

export default Settings;