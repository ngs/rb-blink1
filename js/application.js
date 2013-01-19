(function() {

  (function(window, $) {
    return $(function() {
      var base, input, resultList, search, searchIndex;
      resultList = $('#search-results');
      searchIndex = window.searchIndex;
      input = $('#search-query');
      base = $("script[src$='index.js']").attr('src').replace(/^([^j]*)js.*/, function(a, b) {
        return b;
      });
      search = function() {
        var re, res, val;
        val = input.val();
        if (val.length > 0) {
          re = new RegExp(val, 'gi');
          res = $.grep(searchIndex, function(a, b) {
            return re.test(a.method);
          });
        } else {
          res = searchIndex;
        }
        if (res && res.length > 0) {
          resultList.html(res.map(function(a) {
            var method;
            method = a.method.replace(re, function(m) {
              return "<b>" + m + "</b>";
            });
            return "<li>          <a href=\"" + base + a.link + "\">            <strong>" + method + "</strong>            <small>" + a.module + "</small>          </a>        </li>";
          }));
          if (resultList.is(":hidden")) {
            return resultList.fadeIn();
          }
        } else if (resultList.is(":visible")) {
          return resultList.fadeOut(function() {
            return resultList.empty();
          });
        }
      };
      input.bind('keyup', search).bind('focus', search).bind('blur', function() {
        if (resultList.is(":visible")) {
          return resultList.fadeOut();
        }
      });
      return $('navbar-search').bind('submit', function() {
        return false;
      });
    });
  })(window, $);

}).call(this);
