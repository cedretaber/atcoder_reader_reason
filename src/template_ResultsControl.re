module RR = ReasonReact;

let component = RR.statelessComponent("ResultsControl");

let make = (~dispatcher, ~userId, _children) => {
  ...component,
  render: _self =>
    <Molecules.InputBox
      onChange=(dispatcher#changeUserId)
      onClick=(dispatcher#fetchResults)
      inputValue=userId
      buttonValue={j|取得|j}
    />
}