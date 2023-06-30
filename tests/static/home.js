function alertOC () {

    $("#alert-button")[0].onclick = function () {
      $.ajax({
        url: "/json",
        method: "GET"
      }).done(function(resp) {
        console.log(resp);
      })
    }

}
