# DEncryptor
Encryptor and decryptor for those whose want additional data security 

## Usage
### Using in interactive mode
Run <code>DEncryptor.exe</code> and enter relevant information when prompted.

### Using in the non-interactive mode
To encrypt a file using four-level envelope:

<code> DEncryptor.exe -e Filename.ext -c E </code>

To decrypt a file encrypted using four-level envelope:

<code> DEncryptor.exe -d Filename.ext -c E</code>

#### Options available in the non-interactive mode:
<dl>
	<dt>-e <filename></dt>
    <dd> Encrypt the specified file</dd>
	<dt>-d <filename></dt>
    <dd> Decrypt the specified file</dd>
	<dt>-c <Option></dt>
    <dd> Set the cipher to use. <p>Default cipher is 'Caesar cipher' </p>
	<table>
		<tr>
			<td><strong> Cipher </strong></td>
			<td><strong> Option </strong></td>
		</tr>
		<tr>
			<td> Four-Level Envelope </td>
			<td> E </td>
		</tr>
		<tr>
			<td> Caesar cipher </td>
			<td> C </td>
		</tr>
		<tr>
			<td> Vigenere's cipher </td>
			<td> V </td>
		</tr>
		<tr>
			<td> Alberti's disk cipher </td>
			<td> A </td>
		</tr>	
		<tr>
			<td> Playfair cipher </td>
			<td> P </td>
		</tr>
         </table>
    </dd>
	<dt>-o <filename></dt>
    <dd> Specify output file          
          <p>Default output file is named 'outfile'</p>
          <p>Use 'console' as file name to print output on console </p> 
    </dd>
  <dt>- i</dt>
    <dd>Use in interactive mode</dd>
</dl>

## Screenshots (Interactive mode)
<img src="https://github.com/InputBlackBoxOutput/DEncryptor/blob/master/img/V1-E%20Screenshot_E.png" alt="img/V1-E Screenshot_E.png">
<img src="https://github.com/InputBlackBoxOutput/DEncryptor/blob/master/img/V1-E%20Screenshot_D.png" alt="img/V1-E Screenshot_D.png">

## For Developers
You may contibute to this project by developing features.

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

View documentation at https://inputblackboxoutput.github.io/DEncryptor/

## Disclaimer:
*This application has not been designed to deal with highly sensitive data.*

*Under no circumstances will the creator/s of this application be held responsible or liable in any way for any claims, damages, losses, expenses, costs or liabilities whatsoever (including, without limitation, any direct or indirect damages for loss of profits, business interruption or loss of information) resulting or arising directly or indirectly from your use of or inability to use this application even if the creator/s of this application have been advised of the possibility of such damages in advance.*

## License
GNU Lesser General Public License v3.0

## Made with lots of ⏱️, 📚 and ☕ by InputBlackBoxOutput
