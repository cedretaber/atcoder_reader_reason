module RR = ReasonReact;

module RD = ReactDOMRe;

module RE = ReactEvent;

let s = str => RR.string(str);

type state = {
  userId: string,
  resultList: list(Result.t)
};

type action =
  | FetchResults
  | SuccessFetchResults(Js.Json.t)
  | FailureFetchResults
  | ChangeUserId(string);

let initialState = (userId, ()) => {
  let userId =
    switch (userId) {
    | Some(userId) => userId;
    | None => "";
    };
  { userId, resultList: [] };
};

let result_of_json = json => Js.Json.(
  switch (decodeObject(json)) {
  | None => None
  | Some(obj) =>
    let get = Js.Dict.get(obj);
    let flatMap = Belt.Option.flatMap;
    let map = Belt.Option.map;
    switch (
      get("id") |. flatMap(decodeNumber) |. map(int_of_float),
      get("user_id") |. flatMap(decodeString),
      get("contest_id") |. flatMap(decodeString),
      get("problem_id") |. flatMap(decodeString),
      get("result") |. flatMap(decodeString) |. map(Result.type_of_string),
      get("point") |. flatMap(decodeNumber),
      get("epoch_second") |. flatMap(decodeNumber) |. map(int_of_float),
      get("execution_time") |. flatMap(decodeNumber) |. map(int_of_float),
      get("language") |. flatMap(decodeString),
      get("length") |. flatMap(decodeNumber) |. map(int_of_float)
    ) {
    | (
      Some(id),
      Some(userId),
      Some(contestId),
      Some(problemId),
      Some(result),
      Some(point),
      Some(epochSecond),
      Some(executionTime),
      Some(language),
      Some(length)
    ) => Some({
        Result.id, userId, contestId,
        problemId, result, point,
        epochSecond, executionTime, language,
        length
      });
    | _ => None;
    }
  }
)

let reducer = (action, state) =>
  switch (action, state) {
  | (FetchResults, {userId}) =>
    if (userId == "") {
      RR.NoUpdate;
    } else {
      let url = {j|https://kenkoooo.com/atcoder/atcoder-api/results?user=$userId|j};
      RR.SideEffects(Js.Promise.(self =>
        Fetch.fetch(url)
        |> then_(Fetch.Response.json)
        |> then_(json => resolve(self.send(SuccessFetchResults(json))))
        |> catch(_ => resolve(self.send(FailureFetchResults)))
        |> ignore
      ));
    };
  | (SuccessFetchResults(json), _) =>
      let open Js.Json;
      let resultArray =
        decodeArray(json)
        |. Belt.Option.getWithDefault([||]);
      let resultList =
        Array.fold_right(
          (json, acc) => {
            switch (result_of_json(json)) {
            | Some(result) => [result, ...acc];
            | None => acc;
            }
          },
          resultArray,
          []
        );
      RR.Update({ ...state, resultList });
  | (FailureFetchResults, _) =>
    RR.NoUpdate;
  | (ChangeUserId(userId), _) =>
    RR.Update({ ...state, userId });
  };

let didMount = self => self.RR.send(FetchResults);

class dispatcher ('self) (self: 'self) = {
  as _;
  pub changeUserName = event => {
    let userId = (RE.Form.target(event))##value;
    self.RR.send(ChangeUserId(userId));
  };
  pub fetchResults = event => {
    RE.Mouse.preventDefault(event);
    self.RR.send(FetchResults);
  }
}

let component = ReasonReact.reducerComponent("App");

let render = self => {
  let {userId, resultList} = self.RR.state;
  let dispatcher = (new dispatcher)(self);
  <div className="atcoder-reader-main container">
    <h1 className="title is-1">(s("ATCODER READER"))</h1>
    <Template.ResultsControl dispatcher userId />
    <ResultList resultList />
  </div>
}

let make = (~userId, _children) => {
  ...component,
  initialState: initialState(userId),
  reducer,
  didMount,
  render
};