module RR = ReasonReact;

let component = RR.statelessComponent("InputBox");

let make = (~onChange, ~onClick, ~inputValue, ~buttonValue, _children) => {
  ...component,
  render: _self =>
    <div className="field has-addons">
      <div className="control">
        <Atom.Input onChange value=inputValue />
      </div>
      <div className="control">
        <Atom.Button onClick value=buttonValue />
      </div>
    </div>
};