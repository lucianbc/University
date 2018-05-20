<%@ page import="com.lucianbc.pao.studenti.data.Student" %>
<%@ page import="java.util.List" %><%--
  Created by IntelliJ IDEA.
  User: lucian
  Date: 20.05.2018
  Time: 17:43
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
    <title>Studenti</title>
    <style>
      .user-list-container {
        display: flex;
        height: 100vh;
        align-items: center;
        justify-content: center;
        flex-direction: column;
      }
      table, th, td {
        border: 2px solid black;
        border-collapse: collapse;
      }
    </style>
  </head>
  <body>
    <div class="user-list-container">
      Studenti:
      <table>
        <tr>
          <th>Nume</th>
          <th>Absente</th>
        </tr>
        <%
          List<Student> stds = ((List<Student>)request.getAttribute("studenti"));
          for (Student std : stds) {
        %> <tr><td> <a href="./student?id=<%out.print(std.getId());%>"> <%out.print(std.getNume());%> </a> </td> <td><%out.print(std.getAbsente());%></td> </tr> <%
          }
        %>
      </table>
    </div>
  </body>
</html>
