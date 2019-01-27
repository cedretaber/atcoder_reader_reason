open Jest;
open Expect;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

let setup = (handleChange, value) =>
  Enzyme.shallow(<Atom.Input onChange=handleChange value />);

describe("Atom.Input", () => {
  let module ES = Enzyme.Shallow;

  test("render with a value", () => {
    let inputValue = "test input value";
    let wrapper = setup(_ => (), inputValue);
    expect(wrapper |> ES.is({j|input[className="input"][type="text"][value="$(inputValue)"]|j})) |> toBe(true);
  });

  test("on change a text", () => {
    let changed = ref("");
    let wrapper = setup(e => { changed := e->ReactEvent.Form.target##value; ()}, "");
    let newValue = "new value";
    wrapper |> ES.simulate1("change", [%bs.obj { target: { value: newValue } }]);
    expect(changed^) |> toBe(newValue);
  });
});