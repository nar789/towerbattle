<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>

<?	

	include ("dblib.php");


	$response = array();
	if (isset($_POST['email'])&& isset($_POST['password'])) {

		$email = $_POST['email'];
		$password = $_POST['password'];
		$account= $_POST['account'];
		

		$connect = mysql_connect($host,$user,$pass) or die("SQL server에 연결할 수 없습니다."); 
		mysql_select_db($db,$connect);
		
		$result = mysql_query("select password,account from user where BINARY email='".$email."'");
		if($row=mysql_fetch_array($result))
		{
				if(strcmp($password,'')==0)
					$password=$row['password'];
				if(strcmp($account,'')==0)
					$account=$row['account'];
				
				$result = mysql_query("update user set password='".$password."', account='".$account."' where BINARY email='".$email."'");
				if($result!=NULL)
				{
					echo "1:Success!<br>";
					echo "E-Mail:".$email."<br>"."Password:"."[암호화]"."<br>"."Account:".$account;
				}
				else{
					echo "Fail!";
				}
		}else{
			echo "해당하는 이메일이 없습니다.";
		}
	} else {
    
    
		echo "0:ErrorMessage : value of email or password is null!<br>";
	}
	
	echo "<br><a href='admin.php'>관리자페이지로</a>";



	
?>