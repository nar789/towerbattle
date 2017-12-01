<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>

<?

	include ("dblib.php");
	$response = array();
	if (isset($_POST['email'])) {

		$email = $_POST['email'];
		

		$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
		mysql_select_db($db,$connect);
		
		$is = mysql_query("select password from user where BINARY email='".$email."'");
		if(mysql_fetch_array($is))
		{
		
			$result = mysql_query("update user set cash=1 where BINARY email='".$email."'");
			if($result)
			{
					echo "1:Success!";
			}
		}
		else{
					echo "0:해당하는 이메일이 없습니다.";
		}
		
		
	} else {
    
    
		echo "0:ErrorMessage : value of email or password is null!<br>";
	}
	
	echo "<br><a href='admin.php'>관리자페이지로</a>";



	
?>