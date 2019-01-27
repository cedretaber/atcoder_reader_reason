open Jest;
open Expect;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());


let setup = (~onClick=(_ => ()), ~onChange=(_ => ()), userId) => {
  let dummyDispatcher = {
    as _;
    pub changeUserName = onChange;
    pub fetchResults = onClick;
  };
  Enzyme.mount(<Template.ResultsControl dispatcher=dummyDispatcher userId />);
}

describe("Template.ResultsControl", () => {
  let module EM = Enzyme.Mount;

  test("render with text input", () => {
    let userId = "test user id";
    let wrapper = setup(userId);
    let textInput =
      wrapper
      |> EM.find({j|input[type="text"][value="$(userId)"]|j})
      |> EM.first;
    expect(EM.length(textInput)) |> toBe(1);
  });

  test("render with button input", () => {
    let wrapper = setup("test user id");
    let textInput =
      wrapper
      |> EM.find({j|input[type="submit"][value="取得"]|j})
      |> EM.first;
    expect(EM.length(textInput)) |> toBe(1);
  });

  test("change input", () => {
    let userId = ref("");
    let wrapper =
      setup(
        ~onChange=(e => { userId := ReactEvent.Form.target(e)##value; () }),
        userId^
      );
    let newUserId = "new user id";
    wrapper
    |> EM.find({j|input[type="text"]|j})
    |> EM.simulate1("change", [%bs.obj { target: {value: newUserId } }]);
    expect(userId^) |> toBe(newUserId);
  });

  test("push button", () => {
    let count = ref(0);
    let wrapper =
      setup(
        ~onClick=(_ => { count := count^ + 1; () }),
        ""
      );
    wrapper
    |> EM.find({j|input[type="submit"]|j})
    |> EM.simulate("click");
    expect(count^) |> toBe(1);
  });
});