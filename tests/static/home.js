function alertOC () {

    $("#alert-button")[0].onclick = function () {
      $.ajax({
        url: "/code",
        method: "GET",
      }).done(function(resp) {
        console.log(resp);
      })
    }

}
