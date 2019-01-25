module RR = ReasonReact;

let component = RR.statelessComponent("Button");

let make = (~onClick, ~value, _children) => {
  ...component,
  render: _self => <input className="input" type_="submit" onClick value />
};