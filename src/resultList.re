module ResultType = Result;

module RR = ReasonReact;

let s = str => RR.string(str);

let resultSet = (contestId, resultList) =>
  [
    <th colSpan=6>(s(contestId))</th>,
    ...List.map(result => <Result result />, resultList)
  ]
  |> Array.of_list;

let component = RR.statelessComponent("ResultList");

let make = (~resultList, _children) => {
  ...component,
  render: _self => {
    let module SMap = Belt.Map.String;
    let resultList = List.sort(
      ({ResultType.epochSecond: e1}, {epochSecond: e2}) => compare(e2, e1),
      resultList
    );
    let (resultMap, contestList) = List.fold_right(
      ({ResultType.contestId} as result, (acc, contests)) =>
        if (SMap.has(acc, contestId)) {
          (
            SMap.update(
              acc,
              contestId,
              fun
              | (Some(results)) => Some([result, ...results])
              | None => None
            ),
            contests
          )
        } else {
          (
            SMap.set(acc, contestId, [result]),
            [contestId, ...contests]
          )
        },
      resultList,
      (SMap.empty, [])
    );
    let resultList = List.fold_right(
      (contestId, acc) =>
        switch (SMap.get(resultMap, contestId)) {
        | Some(results) => [resultSet(contestId, results), ...acc]
        | None => acc
        },
      contestList,
      []
    )
    |> Array.of_list
    |> Belt.Array.concatMany;
    <table className="table">
      <thead>
        <tr>
          <td>(s({j|問題|j}))</td>
          <td>(s({j|結果|j}))</td>
          <td>(s({j|点数|j}))</td>
          <td>(s({j|日時|j}))</td>
          <td>(s({j|時間|j}))</td>
          <td>(s({j|言語|j}))</td>
        </tr>
      </thead>
      <tbody>
        ...resultList
      </tbody>
    </table>;
  }
};