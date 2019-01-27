type t = {
  fetchResults: string => Js.Promise.t(Js.Json.t)
};

let make = urlBuilder => {
  fetchResults: userId => {
    Fetch.fetch(urlBuilder(userId))
    |> Js.Promise.then_(Fetch.Response.json)
  }
};