function alertOC () {
  

    const obj = {"hello": 2};


    $("#alert-button")[0].onclick = function () {
      $.ajax({
        url: "/json",
        method: "POST",
        data: "fewhfwefewo",
        contentType: "application/json"
      }).done(function(resp) {
        console.log(resp);
      })
    }

}
