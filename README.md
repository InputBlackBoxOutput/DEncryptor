# DEncryptor

## Usage
### Using in interactive mode
Run <code>DEncryptor.exe</code> and enter relevant information when prompted.

### Using in the non-interactive mode
To encrypt a file using default settings:

<code> DEncryptor.exe -e Filename.ext </code>

To decrypt a file encrypted using default settings:

<code> DEncryptor.exe -d Filename.ext </code>

#### Options available in the non-interactive mode:
<dl>
  <dt>-e <filename></dt>
    <dd> Encrypt the specified file</dd>
  
  <dt>-d <filename></dt>
    <dd> Decrypt the specified file</dd>
  
  <dt>-c <Option></dt>
    <dd> Set the cipher to use. 
    <br> Default cipher is 'Caesar cipher'    
    <table>
      <thead>
        <td>Cipher </td>
        <td>Option</td>
      </thead>
      <tr>
        <td>Envelope </td>
        <td>E</td>
      </tr>
      <tr>
        <td>Caesar cipher </td>
        <td>C</td></tr>
      <tr>
        <td>Vigenere's cipher </td>
        <td>V</td></tr>
      </tr>
      <tr>
        <td>Alberti's disk cipher </td>
        <td>A</td></tr>
      </tr>
      <tr>
        <td>Playfair cipher </td>
        <td>P</td></tr>
      </tr>
    </table>
    </dd>
  
  <dt>-o <filename></dt>
    <dd> Specify output file
         <br> Default output file is named 'output.txt'
    </dd>
  
  <dt>- i</dt>
    <dd>Use in interactive mode</dd>
</dl>

## Screenshot
![](screenshot.png)

## Disclaimer:
*This application has not been designed to deal with highly sensitive data.*

*Under no circumstances will the creator/s of this application be held responsible or liable in any way for any claims, damages, losses, expenses, costs or liabilities whatsoever (including, without limitation, any direct or indirect damages for loss of profits, business interruption or loss of information) resulting or arising directly or indirectly from your use of or inability to use this application even if the creator/s of this application have been advised of the possibility of such damages in advance.*

## Made with lots of ⏱️, 📚 and ☕ by InputBlackBoxOutput
