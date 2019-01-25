module RR = ReasonReact;

let component = RR.statelessComponent("Container");

let make = children => {
  ...component,
  render: _self => <div className="atcoder-reader-main container"> ...children </div>
};