#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "neurolib.h"
//library given to us for conversation mode



// function for doing a very naive syntax check on json, just checking for valid
// braces and quotes
int validJson(const char *buffer, int buffSize) {
  // we put the json into a string buffer beforehand
  // we loop over every character in the string and check if it's a curly/square
  // bracket, outside of a string. We also count total number of quotes and
  // various other small checks
  int curlyCount = 0;
  int bracesCount = 0;
  int quoteCount = 0;
  int inString = 0;
  int tempQuotes = 0;
  int hasColon = 0;

  //loop over the entire json
  for (int i = 0; i < buffSize; i++) {
    
    // check if quote is outside of string. We begin by checking if the last
    // character is a backslash. If it is, check if the amount of preceding
    // backslashes is even or odd and act accordingly
    if (buffer[i] == '\"' && (i == 0 || buffer[i - 1] != '\\')) {
      // this toggles between being in a string or being out of it
      inString = 1 ^ inString;
      quoteCount++;
      tempQuotes++;
    } else if (buffer[i] == '\"' && (i == 0 || buffer[i - 1] == '\\')) {
      int backslashCounter = 0;
      for (int j = i - 1; j >= 0; j--) {
        if (buffer[j] != '\\') break;

        backslashCounter++;
      }
      // if backslashes are odd, it's in a string so move on
      if (backslashCounter % 2 != 0) continue;
      // otherwise, it means it's outside of a string.
      else {
        inString = 1 ^ inString;
        quoteCount++;
        tempQuotes++;
      }
    }

    // check for colon. In every line with more than one quote, it would mean
    // there's a key, therefore there has to be a value too. Naive check to catch
    // some edge cases.
    if (buffer[i] == ':' && inString == 0) hasColon++;
    // count brackets, square brackets and other various checks.
    if (buffer[i] == '{' && inString == 0)
      curlyCount++;
    else if (buffer[i] == '}' && inString == 0)
      curlyCount--;
    else if (buffer[i] == '[' && inString == 0)
      bracesCount++;
    else if (buffer[i] == ']' && inString == 0)
      bracesCount--;
    else if (buffer[i] == '\n' && inString == 1)
      return 1;
    else if (buffer[i] == '\n' && inString == 0) {
      if (tempQuotes != 0 && hasColon == 0) return 1;

      tempQuotes = 0;
      hasColon = 0;

    }
    // check if we have letters outside of quotes, which isnt allowed. However,
    // except null, true, false.
    else if (inString == 0 && (buffer[i] >= 59 && buffer[i] <= 90))
      return 1;
    else if (inString == 0 && (buffer[i] != 'n') && (buffer[i] != 'u') &&
             (buffer[i] != 'l') && (buffer[i] != 't') && (buffer[i] != 'r') &&
             (buffer[i] != 'e') && (buffer[i] != 'f') && (buffer[i] >= 'a') &&
             (buffer[i] <= 's'))
      return 1;
    else if (inString == 0 &&
             ((buffer[i] == 'n') || (buffer[i] == 't') || (buffer[i] == 'f'))) {
      // some edge case: if we do have null, true or false, then before that
      // there must be a colon (NAIVE check)
      for (int j = i - 1; j >= 0; j--) {
        if (isspace(buffer[j]) == 0 && (buffer[j] != ':'))
          return 1;
        else if (buffer[j] == ':')
          break;
      }
    }
  }

  // if either of the 2 counts are not 0 that means that one bracket pair is not
  // complete so return 1
  if ((curlyCount != 0) || (bracesCount != 0) || (quoteCount % 2 != 0))
    return 1;

  // return 0 otherwise
  return 0;
}

// function to read a json file and get its content
char *getResponse(char *buffer, long size) {
  // do naive weighted check for verifying validity of json
  if (validJson(buffer, size) != 0) {
    fprintf(stderr, "Not an accepted JSON!\n");
    free(buffer);
    exit(1);
  }

  // naively check if the path that we are looking for exists
  if (strstr(buffer, "\"choices\"") == NULL ||
      strstr(buffer, "\"message\"") == NULL ||
      strstr(buffer, "\"content\"") == NULL) {
    fprintf(stderr, "Not an accepted JSON!\n");
    free(buffer);
    exit(1);
  }
  // get a pointer where the content part that we are looking for starts
  char *index = strstr(buffer, "\"content\"");

  // skip the "content" part to move on to its value:
  index += strlen("\"content\"");
  while ((isspace(*index) != 0) || (*index == ':')) index++;

  // skip first quote (if not quote, return error)
  if (*index != '\"') {
    fprintf(stderr, "Not an accepted JSON!\n");
    free(buffer);
    exit(1);
  }
  index++;
  // counter to get size of the message. Stop until " is found. Warning: if
  // content has " the result will be incorrect.
  int counter = 0;
  int end = strlen(index);

  // break when done with content
  while (counter < end) {
    if (index[counter] == '\"' && (counter == 0 || index[counter - 1] != '\\'))
      break;
    // this is the same logic as in the validJson function where we look for the
    // amount of preceding backslashes before the quotes.
    else if (index[counter] == '"' &&
             (counter == 0 || index[counter - 1] == '\\')) {
      int backslashCounter = 0;
      for (int j = counter - 1; j >= 0; j--) {
        if (index[j] != '\\') break;

        backslashCounter++;
      }
      
      if (backslashCounter % 2 != 0)
        continue;
      else
        break;
    }
    counter++;
  }

  // keep counter for the actual result, so make a copy
  int counter2 = counter + 1;
  // another naive check for missing quotes: after having checked for quotes,
  // there is no way we will see a colon, but rather a comma, or a quote.
  while (counter2 < end) {
    if (index[counter2] == ':') {
      fprintf(stderr, "Not an accepted JSON!\n");
      free(buffer);
      exit(1);
    } else if (index[counter2] == '\"')
      break;
    counter2++;
  }

  // counter+1 size to store null byte (result is the string for the content)
  char *result = malloc((counter + 1) * sizeof(char));
  // copy the content to result string
  for (int i = 0; i < counter; i++) result[i] = index[i];
  // null terminate string
  result[counter] = '\0';

  // newline ('\n') is currently stored as a literal, eg as \\n, so we need to
  // find and make real newlines.
  int length = strlen(result);
  for (int i = 0; i < length; i++) {
    if (result[i] == '\\' && i + 1 < length && result[i + 1] == 'n') {
      result[i] = '\n';
      // shift everything after (i + 1) one step left
      // so we remove the 'n' character.
      for (int j = i + 1; j < length; j++) {
        result[j] = result[j + 1];
      }
      // we removed one character, so the new length is one less
      length--;
    }
  }
  // same thing for quotes.
  
  for (int i = 0; i < length; i++) {
    if (result[i] == '\\' && i + 1 < length && result[i + 1] == '"') {
      result[i] = '"';

      // shift everything after (i + 1) one step left
      // so we remove the 'n' character.
      for (int j = i + 1; j < length; j++) {
        result[j] = result[j + 1];
      }

      // we removed one character, so the new length is one less
      length--;
    }
  }

  // same thing for back slashes.
  for (int i = 0; i < length; i++) {
    if (result[i] == '\\' && i + 1 < length && result[i + 1] == '\\') {
      result[i] = '\\';

      // shift everything after (i + 1) one step left
      // so we remove the 'n' character.
      for (int j = i + 1; j < length; j++) {
        result[j] = result[j + 1];
      }

      // we removed one character, so the new length is one less
      length--;
    }
  }

  return result;
}

// driver code
int main(int argc, char *argv[]) {
  // initializing mode:
  // mode 0 will mean the bot is in extract mode, mode 1 will mean the bot is in
  // conversation mode!
  int mode = -1;
  if (argc != 3 && argc != 2) {
    fprintf(stderr, "Usage: ./jason --mode <JSON>");
    return 1;
  }
  if (argc == 3 && strcmp(argv[1], "--extract") == 0)
    mode = 0;
  else if (argc == 2 && strcmp(argv[1], "--bot") == 0)
    mode = 1;
  else {
    fprintf(stderr, "Usage: ./jason --mode <JSON>\n");
    return 1;
  }

  // FIRST CASE: Extract mode
  if (mode == 0) {
    FILE *data = fopen(argv[2], "r");
    if (data == NULL) {
      fprintf(stderr, "Failed to open json file!\n");
      return 1;
    }
    // extract content from given json
    // use fseek and ftell to get file size (move pointer to end of file stream,
    // get offset, mvoe it back again)
    fseek(data, 0, SEEK_END);
    long size = ftell(data);
    fseek(data, 0, SEEK_SET);

    // allocate size bytes for storing the json in a string buffer
    char *buffer = malloc(size * sizeof(char));
    fread(buffer, 1, size, data);
    buffer[size] = '\0';

    // get result
    char *result = getResponse(buffer, size);

    // insurance check that result isnt null before printing it
    if (result != NULL) printf("%s", result);

    // deallocate memory etc
    fclose(data);
    free(result);
    free(buffer);
  }
  // SECOND CASE: Conversation mode
  else if (mode == 1) {
    // initialize string to store userprompt
    char *userPrompt = NULL;
    // according to neurolib.h, call this function once for every usage of a
    // function inside neurolib.h
    neurosym_init();
    // Buffer to hold string of arbitary size (read entire line and then get
    // each string seperately)
    char *line = NULL;
    size_t n = 0;
    

    // get user prompt
    printf("> What would you like to know? ");
    while (getline(&line, &n, stdin) != -1) {
      userPrompt = strdup(line);
      size_t sSize = strlen(userPrompt);
      if(userPrompt[sSize-1] == '\n')
        userPrompt[sSize-1] = '\0';      

      
      // use response functino to get the AI response based on the user prompt
      char *responseJSON = response(userPrompt);

      //syntax check the json that is generated as a string
      if(validJson(responseJSON, strlen(responseJSON)) != 0)
      {
        fprintf(stderr, "Not an accepted JSON!\n");
        free(userPrompt);
        free(responseJSON);
        return 1;
      }

      // store content
      char *goodResponse = getResponse(responseJSON, strlen(responseJSON));
      if(goodResponse != NULL)
        printf("%s\n", goodResponse);


      //deallocate memory after each iteration
      free(goodResponse);
      free(userPrompt);
      free(responseJSON);
      printf("> What would you like to know? ");
    }
    free(line);
    printf("Terminating\n");
  }

  // terminate gracefully.
  return 0;
}
