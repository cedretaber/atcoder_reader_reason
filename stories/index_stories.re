open BsStorybook;
open Story;

let _module = [%bs.raw "module"];

module Knobs = {
  include(Knobs);

  [@bs.val] [@bs.module "@storybook/addon-knobs"]
  external withKnobs: Main.decorator = "";
};

storiesOf("Button", _module)
|. addDecorator(Knobs.withKnobs)
|. add("with simple label", () => {
  let label = Knobs.text(~label="Button text", ~defaultValue="Click me!", ());
  <Atom.Button onClick=(Action.action("Clicked!")) value=label />
});

storiesOf("Input", _module)
|. add("with no input", () => {
  <Atom.Input onChange=(Action.action("Changed!")) value="" />
});

storiesOf("ResultsControl", _module)
|. addDecorator(Knobs.withKnobs)
|. add("Simple usage", () => {
  let dispatcher = {
    as _;
    pub changeUserName = Action.action("Change user ID.");
    pub fetchResults = Action.action("Fetch results.");
  };
  let userId = Knobs.text(~label="User ID", ~defaultValue="", ());
  <Template.ResultsControl dispatcher userId />
});