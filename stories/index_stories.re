open BsStorybook;
open Story;

let module_ = [%bs.raw "module"];

module Knobs = {
  include(Knobs);

  [@bs.val] [@bs.module "@storybook/addon-knobs"]
  external withKnobs: Main.decorator = "";
};

storiesOf("Button", module_)
->addDecorator(Knobs.withKnobs)
->add("with simple label", () => {
  let label = Knobs.text(~label="Button text", ~defaultValue="Click me!", ());
  <Atom.Button onClick=(Action.action("Clicked!")) value=label />
});

storiesOf("Input", module_)
->add("with no input", () => {
  <Atom.Input onChange=(Action.action("Changed!")) value="" />
});

storiesOf("ResultsControl", module_)
->addDecorator(Knobs.withKnobs)
->add("Simple usage", () => {
  let dispatcher = {
    as _;
    pub changeUserId = Action.action("Change user ID.");
    pub fetchResults = Action.action("Fetch results.");
  };
  let userId = Knobs.text(~label="User ID", ~defaultValue="", ());
  <Template.ResultsControl dispatcher userId />
});