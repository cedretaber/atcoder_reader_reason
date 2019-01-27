let maybeUser = switch [%bs.raw {|(location.search.match(/[?&]user=(\w+)/) || [0,""])[1]|}] {
| "" => None;
| userId => Some(userId);
};

let apiClient = ApiClient.make(userId => {j|https://kenkoooo.com/atcoder/atcoder-api/results?user=$userId|j});

ReactDOMRe.renderToElementWithId(<App userId=maybeUser apiClient />, "app");