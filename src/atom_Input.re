module RR = ReasonReact;

let component = RR.statelessComponent("Input");

let make = (~onChange, ~value, _children) => {
  ...component,
  render: _self => <input className="input" type_="text" onChange value />
};
  