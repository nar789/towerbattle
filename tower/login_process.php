<?

	include ("dblib.php");
	$response = array();


		$email = $_POST['email'];
		$password = $_POST['password'];
		$connect = mysqli_connect($host,$user,$pass,$user) or die("SQL server에 연결할 수 없습니다."); 
		//mysql_select_db($db,$connect);
		$result = mysqli_query($connect,"select password from user where BINARY email='".$email."'");
		$response=mysqli_fetch_array($result);
		if($response==NULL)
			echo "1:Incorrect E-mail!".$email;
		else{
			if(strcmp($response['password'],$password)==0)
				echo "3:Success!!!";
			else
				echo "2:Incorrect Password!".$password;
			
		}

	
	//echo "<br><a href='admin.php'>관리자페이지로</a>";
	mysqli_close($connect);


	
?>