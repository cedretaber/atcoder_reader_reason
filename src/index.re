let maybeUser = switch [%bs.raw {|(location.search.match(/[?&]user=(\w+)/) || [0,""])[1]|}] {
| "" => None;
| userId => Some(userId);
};

ReactDOMRe.renderToElementWithId(<App userId=maybeUser />, "app");