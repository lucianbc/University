<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
    <body>
        <%
            Boolean b = (Boolean) request.getSession().getAttribute("admin");
            if (b == null || !b) {
                out.print("Accesul interzis");
            } else  {
                out.print("Accesul permis");
            }
        %>
    </body>
</html>