<%--
  Created by IntelliJ IDEA.
  User: lucian
  Date: 20.05.2018
  Time: 14:33
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>$Title$</title>
  </head>
  <body>
    Here's a number: <%
      try {
        Double n = (Double) request.getSession().getAttribute("number");
        out.write(Double.toString(n));
      } catch (NullPointerException e) {
          out.write("No num");
      }
    %>
  </body>
</html>
