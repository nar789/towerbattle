<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>
<font size=20>Welcome Tower Battle Admin Page!</font><br>
<?
	include ("dblib.php");

	$response = array();
	if (isset($_POST['email'])&& isset($_POST['password'])) {

		$email = $_POST['email'];
		$password = $_POST['password'];
		if(strcmp($email,'tower')==0)
		{

			$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
			mysql_select_db($db,$connect);
			$result = mysql_query("select password from user where BINARY email='tower'");
			$response=mysql_fetch_array($result);
			if(strcmp($response['password'],$password)==0)
			{
					$result = mysql_query("select email,account,point,cash from user");
					echo "<table border=1 cellspacing=0 bodercolor='#3c4b4e'>";
					
					
					while($row=mysql_fetch_array($result))
					{
						echo "<tr>";
						echo "<td bgcolor='#8fb7bf'>E-MAIL</td><td>".$row['email']."</td><td bgcolor='#8fb7bf'>Account Number</td><td>".$row['account']."</td>"."<td bgcolor='#8fb7bf'>POINT</td><td>".$row['point']."</td>"."<td bgcolor='#8fb7bf'>현금전환신청</td>";
						if($row['cash']==0)
							echo "<td>미신청</td>";
						else
							echo "<td bgcolor='#ff3131'><font color='white'>신청</font></td>";
						echo "</tr>";
						
					}
					echo "<a href='admin.php'>홈</a><br>";
					echo "<a href='join.php'>회원정보추가</a><br>";
					echo "<a href='alter.php'>회원정보수정</a><br>";
					echo "<a href='delete.php'>회원정보삭제</a><br>";
					echo "<a href='login.php'>로그인테스트</a><br>";
					echo "<a href='getpoint_inputemail.php'>포인트확인</a><br>";
					echo "<a href='getpoint_inputemail.php'>포인트변경</a><br>";
					echo "<a href='notcash_input.php'>포인트전환신청변경</a>";
					
					
					
					
				
			}
			else{
					echo "Not Admin password!";
			}
			
		}
		else{
			echo "Not Admin E-mail!";
		}
		
	} else {
    
    
		echo "0:ErrorMessage : value of email or password is null!<br>";
	}



	
?>