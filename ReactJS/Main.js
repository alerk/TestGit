import React from 'react';
import { render } from 'react-dom'

class Hello extends React.Component {
	render() {
	//JSX code in return function
		return (
		<div>
			<h1> Hello World </h1>
		</div>
		);
	}
}

render(<Hello/>. document.getElementById('app'));
