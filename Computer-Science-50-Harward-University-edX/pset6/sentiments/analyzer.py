import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        # empty lists for words
        self.positives_list = []
        self.negatives_list = []

        # open files
        positives_file = open(positives, 'r')
        negatives_file = open(negatives, 'r')

        # read every line from file and append to list if word
        for line in positives_file:
            if line[0].isalpha():
                self.positives_list.append(line.strip())

        # read every line from file and append to list if word
        for line in negatives_file:
            if line[0].isalpha():
                self.negatives_list.append(line.strip())


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # extracts words from text to list
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        # initial value for sum
        sentiments_sum = 0

        # count sentiments value of text
        for word in tokens:
            if word.lower() in self.positives_list:
                sentiments_sum += 1

            elif word.lower() in self.negatives_list:
                sentiments_sum -= 1


        return sentiments_sum
