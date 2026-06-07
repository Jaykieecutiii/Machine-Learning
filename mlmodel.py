import pandas as pd
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
import joblib

df = pd.read_csv("battery_data.csv")

X = df[["voltage", "current", "time", "mAh"]]
y = df["SOH"]

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)

model = RandomForestRegressor(n_estimators=150)
model.fit(X_train, y_train)

print("Score:", model.score(X_test, y_test))

joblib.dump(model, "soh_model.pkl")