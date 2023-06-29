function alertOC () {

    $("#alert-button")[0].onclick = function () {
      let url = "/hello?";
      const params = "key1=hello&key2=hello";
      url += (params);
      console.log(url);
      $.ajax({
        url: url,
        method: "GET"
      }).done(function(resp) {
        console.log("here");
      })
    }

}
