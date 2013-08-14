/**
 * Provides javascript for the Chuck Norris Joke field.
 */
(function ($) {
  Drupal.behaviors.chuck = {
    attach: function(context) {
      $('#field-chuck-submit').live("click", function(event) {
        var url,
            $id = $('#field-chuck-id input').val();

        if ($.isNaN($id)) {
          url = 'http://api.icndb.com/jokes/random';
        }
        else {
          url = 'http://api.icndb.com/jokes/' + $id;
        }
        $.get(url, function(data) {
          $('#field-chuck-id input').val(data.value.id);
          $('#field-chuck-joke input').val(data.value.joke);
        }, "json");
      });
    },
  }
})(jQuery);

