type resultType =
  | AC
  | WA
  | TLE
  | MLE
  | CE
  | Other(string);

let type_of_string =
  fun
  | "AC" => AC
  | "WA" => WA
  | "TLE" => TLE
  | "MLE" => MLE
  | "CE" => CE
  | other => Other(other);

type t = {
  id: int,
  userId: string,
  contestId: string,
  problemId: string,
  result: resultType,
  point: float,
  epochSecond: int,
  executionTime: int,
  language: string,
  length: int
};

module RR = ReasonReact;

let s = str => RR.string(str);

let component = RR.statelessComponent("Result");

let element_of_type =
  fun
  | AC => <span className="has-text-success">(s("AC"))</span>
  | WA => <span className="has-text-danger">(s("WA"))</span>
  | TLE => <span className="has-text-danger">(s("TLE"))</span>
  | MLE => <span className="has-text-danger">(s("MLE"))</span>
  | CE => <span className="has-text-warning">(s("CE"))</span>
  | Other(str) => <span>(s(str))</span>;

let make = (~result as {problemId, result, point, epochSecond, executionTime, language}, _children) => {
  ...component,
  render: _self => {
    let datetime = {
      let open Js.Date;
      let time_t = fromFloat(float_of_int(epochSecond) *. 1000.);
      let date = toLocaleDateString(time_t);
      let time = toLocaleTimeString(time_t);
      {j|$date $time|j}
    };
    <tr>
      <td>(s(problemId))</td>
      <td>(element_of_type(result))</td>
      <td>(s(string_of_int(int_of_float(point))))</td>
      <td>(s(datetime))</td>
      <td>(s(string_of_int(executionTime)))</td>
      <td>(s(language))</td>
    </tr>
  }
}