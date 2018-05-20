<%--
  Created by IntelliJ IDEA.
  User: lucian
  Date: 20.05.2018
  Time: 18:38
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Student</title>
    <style>
        .container {
            display: flex;
            align-items: center;
            justify-content: center;
        }
    </style>
</head>
<body>
    <div class="container">
        <form action="student?id=<%out.print(request.getParameter("id"));%>" method="POST">
            Nume: <input type="text" name="nume" value="${name}">
            <br/>
            Absente: <input type="number" name="absente" value="${abs}">
            <br/>
            <input type="submit" value="Submit">
        </form>
    </div>
</body>
</html>
