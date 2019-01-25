module RR = ReasonReact;

let component = RR.statelessComponent("H1");

let make = children => {
  ...component,
  render: _self => <h1 className="title is-1"> ...children </h1>
};