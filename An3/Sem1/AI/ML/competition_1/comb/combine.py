import pandas as pd
import os


submissions = os.listdir("./submissions")

ans = pd.DataFrame()
for i, submission in enumerate(submissions):
    df = pd.read_csv("./submissions/"+submission)
    ans[i] = df.label


ans["label"] = ans.mode(axis=1)[0]
ans.drop(columns=[i for i in range(len(submissions))], inplace=True)
ans.index += 1
ans.index.name = "id"
print(ans)
ans.to_csv("combined_submissions.csv")
